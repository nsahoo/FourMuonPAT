#! /bin/tcsh -f

foreach file (`cat a.txt`)

	hadd -f deneme.root deneme.root $file

end
