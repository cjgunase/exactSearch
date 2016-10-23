#####################################################################
#this program convert a fasta format to a "spcial" fasta
#format that all sequence will be in the same line, no "\n".
#the purpose for this is to handle the sequence easity and store
# with array.
#
#
###################################################################

#!/usr/local/bin -w
$count = 1;
open(Ref,"28K_20K_smad4_peak.053107.seq.modified.txt");
#open(Ref,"CEL478.fasta");#input file name
open(FH, ">CEL478.fasta.out");#output file name

     while (<Ref>) {
	 chomp();
     #  $line = $_;
	 if (/^>/) {
            @fields = split(/\t/, $_);
            print "\n$fields[0]\t";
            if($count > 1) {
            print FH "\n"; }
            print FH $fields[0] ;
            print FH  "\n";
            $count++;
            #print FH "\t"; 
#	    print ">";
#            print "$fields[0]\n";
          #  print "$fields[1]";
	} else {
            #print "$_";
            print FH $_;
           # print "\n";
	}
     }
close(Ref);
close(FH);

