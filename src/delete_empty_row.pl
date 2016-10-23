#!/usr/bin/perl -w
#this program is to delete all empty lines in the input file ###
#                                                            ###
#                                                            ###
# to run the program: perl delete_empty_row.pl               ###
# then follow the instruction to complete the program        ###
################################################################
print "please input the name of file you want to handle:\n";
$input_file = <STDIN>; 
chomp $input_file;
#open(MYFILE, "clover1.out");
open(MYFILE,"$input_file");
print"please input the name of file your new namefile you want to store the result:\n";
$output_file = <STDIN>;
chomp $output_file;
$final = ">" . $output_file;
open(FH,"$final");
#print FH "Sequence		Motif			Location		Strand		Sequence		Score\n";
while(<MYFILE>){
  chomp();
  if($_){
   print  FH "$_" ;
   print  FH "\n";}
}
close(MYFILE);
close(FH);
