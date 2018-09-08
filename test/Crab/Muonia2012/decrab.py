#!/usr/bin/env python

import distutils
import distutils.fancy_getopt
import os
import sys
import string
import re
import commands


#== Settings ==================================================================


class Color:
  "ANSI escape display sequences"
  info          = "\033[1;34m"
  hilight       = "\033[31m"
  hilight2      = "\033[35m"
  alternate     = "\033[32m"
  extra         = "\033[33m"
  backlight     = "\033[1;37;45m"

  underline     = "\033[4m"
  lessemphasis  = "\033[30m"
  deemphasis    = "\033[1;30m"
  inverse       = "\033[1;37;40m"
  none          = "\033[0m"

class Error:
  "Exit codes"
  none        = 0
  usage       = 1
  input       = 2
  argument    = 3
  execution   = 4

class Settings:
  "Settings for execution etc."

  blurb         = """
Usage: %program% [options] <storage-path...>

Removes duplicate output files as CRAB can generate by running the same job twice.
The file with the largest size is kept per job. If there are ties:
  - TODO (not implemented yet): If crab-dir is provided, prefers the file referred to in the job stdout.
  - Otherwise prefers the file with the later timestamp.

Command-line options can be:
"""
  variables     = distutils.fancy_getopt.FancyGetopt([
                    ("help",                  "h",  "Print this informational message."),
                    ("dry-run",               "d",  "Prints out commands but does not run. Default %dry-run%."),
                    ("crab-dir=",             "c",  "Location of CRAB directory. If provided, prefers output files that match those in the latest log files. Default %crab-dir%."),
                    ("size-leeway=",          "s",  "Maximum fractional difference in sizes to consider files as being the 'same'. Default %size-leeway%."),
                  ])
  options       = { "help"                  : False,
                    "dry-run"               : False,
                    "crab-dir"              : None,
                    "size-leeway"           : "0.01",
                  }
  usage         = None

  getJobIndex   = re.compile(r"_([0-9]+)_([0-9]+)_[a-zA-Z0-9]{3}\.[^.]+$")


#== Functions =================================================================


def convertSetting(setting, convertor, errorMessage):
  """
  Convert the given setting using the form produced by convertor. ValueError's
  are caught and errorMessage is printed, then the application exits. errorMessage
  is a format string taking one string argument, the problematic value.
  """

  try:
    Settings.options[setting] = convertor(Settings.options[setting])
  except ValueError:
    print Color.hilight + (errorMessage % str(Settings.options[setting])) + Color.none
    sys.exit(Error.argument)

  return

def toList(streeng, delimiter = ";"):
  streeng = streeng.strip()
  if streeng == "":   return []
  return string.split(streeng, delimiter)


def parseArgs(args):
  "Parses command-line arguments into options and variables"

  Settings.scriptDir  = os.path.dirname(os.path.abspath(args[0]))
  Settings.blurb      = Settings.blurb.replace("%program%", os.path.basename(args[0]))
  Settings.usage      = string.join(Settings.variables.generate_help(Settings.blurb), "\n")
  for (variable, default) in Settings.options.iteritems():
    if type(default) == type(""):
      Settings.options[variable]  = default.replace("%script-dir%", Settings.scriptDir)
  for (variable, default) in Settings.options.iteritems():
    Settings.usage    = re.compile("%" + variable.replace("-", "-\s*") + "%") \
                          .sub(str(default), Settings.usage)

  try:
    (arguments, options)  = Settings.variables.getopt(args[1:])
  except distutils.errors.DistutilsArgError, details:
    print "Error in command-line:", details
    print Settings.usage
    sys.exit(Error.usage)

  # Get the dictionary of option -> value
  Settings.options.update(dict(Settings.variables.get_option_order()))

  # Special options
  convertSetting("size-leeway",  float,  "%s must be a number.")


  if Settings.options["help"] or len(arguments) < 1:
    print Settings.usage
    print
    sys.exit(Error.none)

  return arguments


def runJob(commandLine, errorMessage=None, logPath=None, verbose=False):
  """
  Runs the specified command, saving the output and checking the status.
  """

  (status, output)  = commands.getstatusoutput(commandLine);
  if logPath:
    logFile = open(logPath, "w")
    logFile.write(output)
    logFile.close()

  if (errorMessage == None and status != 0) or (errorMessage != None and errorMessage in output):
    print Color.hilight + "###", Color.none
    print Color.hilight + "###  PROBLEM    :", Color.none, commandLine.split(" ",1)[0], "exited with error code", status
    print Color.hilight + "###  Command    :", Color.none, commandLine
    print Color.hilight + "###  Output was :", Color.none
    print Color.hilight + "###", Color.none
    print output
    sys.exit(Error.execution)

  if verbose:
    print Color.info, commandLine, Color.none
  if logPath:     print "  ... successful, logged in", logPath
  elif verbose:   print Color.deemphasis + output, Color.none
  return output


def numberFields(x):
  fields          = re.compile("[0-9]+|Inf").findall(x)
  for index in range(len(fields)):
    if fields[index] == "Inf":
      fields[index] = sys.maxint
    else:
      fields[index] = int(fields[index])
  return fields

def nominalOrder(strings):
  getCategory     = re.compile("[0-9]+(?:to(?:[0-9]+|Inf))?")
  categories      = {}
  for x in strings:
    categories.setdefault(string.join(getCategory.split(x), ""), []).append(x)
  
  ordered         = []
  keys            = categories.keys()
  keys.sort()
  for key in keys:
    components    = categories[key]
    components.sort(key=numberFields)
    ordered.append(components)
  return ordered



#== Main Execution Point ======================================================


if __name__ == '__main__':

  storagePaths        = parseArgs(sys.argv)
  for storagePath in storagePaths:
    
    outputFiles       = {}
    for file in os.listdir(storagePath):
      indices         = Settings.getJobIndex.search(file)
      if indices:
        outputFiles.setdefault(int(indices.group(1)), []).append(file)

    noOutput          = []
    oneOutput         = []
    multiOutput       = []
    for (job, files) in outputFiles.iteritems():
      if   len(files) == 0:   noOutput.append(job)
      elif len(files) == 1:   oneOutput.append(job)
      else:                   multiOutput.append((job, files))
    
    print Color.info + storagePath, Color.none
    if len(oneOutput):
      print " ", Color.alternate, "Normal:      ", Color.none, string.join(map(str,oneOutput), " ")
    if len(noOutput):
      print " ", Color.hilight  , "No output:   ", Color.none, string.join(map(str,noOutput ), " ")
    if len(multiOutput):
      print " ", Color.hilight2 , "Multi-output:", Color.none
    
    for (job, files) in multiOutput:
      print " ", Color.hilight2 , " ", "%4d" % job, ":", Color.none,
      duplicates      = []
      for file in files:
        filePath      = os.path.join(storagePath, file)
        numBytes      = float(runJob("dcdu " + filePath).split()[0])
        blurb         = "%25s = %-6s" % (file, runJob("dcdu -h " + filePath).split()[0])
        for index in range(len(duplicates)):
          if abs(duplicates[index][0] - numBytes) <= Settings.options["size-leeway"] * (duplicates[index][0] + numBytes) / 2:
            duplicates[index][1].append((blurb, filePath))
            blurb     = ""
            break
        if blurb:
          duplicates.append([numBytes, [(blurb, filePath)]])
      duplicates.sort(key = lambda x: x[0], reverse = True)
      
      latestTime      = -1
      latestFile      = None
      for (blurb, file) in duplicates[0][1]:
        modTime       = os.stat(file)
        if not latestFile or modTime > latestTime:
          latestTime  = modTime
          latestFile  = file
      
      for (blurb, file) in duplicates[0][1]:
        if file == latestFile:  print Color.extra,
        else:
          print Color.deemphasis,
          if not Settings.options["dry-run"]:
            os.remove(file)
        print blurb, Color.none,
      for timeFiles in duplicates[1:]:
        for (blurb, file) in timeFiles[1]:
          print Color.deemphasis, blurb, Color.none,
          if not Settings.options["dry-run"]:
            os.remove(file)
      
      print
