#!/usr/bin/perl -w
sub TM{
    ($temp) = @_;
    foreach $y(@$temp) {
    if(!(($y eq 'A')||($y eq 'T')||($y eq 'C')||($y eq 'G'))){ return 0;}
                       }
    return 1;}
open(OUT,"motif.fasta");
open(IN, ">motif_temp1");
open(TWO, ">motif_temp2");
while(<OUT>) {
       chomp();
       if(!(/^>/)){
           @temp = split(//,$_);
           if(TM(\@temp)) {
           print IN "$_\n";}
            
           else{
            print TWO "$_\n";}
         }
}
close(TWO);
close(OUT);
close(IN);
