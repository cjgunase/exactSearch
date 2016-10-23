#print "the exact match program begins:\n";;
$count = 1;
#print"please input your gene sequnence(.fasta):\n";
$input_file = $ARGV[0]; chomp $input_file;
open(Ref,"$input_file");
open(FH, ">sequence_temp");#output file name
while (<Ref>) {
    chomp();
    if (/^>/) {
	@fields = split(/\t/, $_);
	if($count > 1) {
	    print FH "@\n";}
	print FH $fields[0];
	print FH "\n";
	$count++;
    }  else{
	print FH $_;
    }
}
print FH "@";
close(Ref);
close(FH);
#print"please input your file(.fasta) containing your motifs\n";
$motif_file = $ARGV[1]; chomp $motif_file;
$search_out = $input_file . "_exact_match.out";
sub TM{
    ($temp) = @_;
    foreach $y(@$temp) {
	if(!(($y eq 'A')||($y eq 'T')||($y eq 'C')||($y eq 'G'))){ return 0;}
    }
    return 1; }
open(OUT1,"$motif_file");
open(OUT2,">motif_temp1");
open(OUT3,">motif_temp2");
while(<OUT1>){
    chomp();
    if(!(/^>/)){
	@temp = split(//,$_);
	if(TM(\@temp)) {
	    print OUT2 "$_\n";}
	else{
	    print OUT3 "$_\n";}
    }
}
close(OUT1);
close(OUT2);
close(OUT3);
    #qx(file/exe/./suffix_tree > suffix_tree_search.out);
    #qx(file/exe/./consenus >> suffix_tree_search.out);
qx(./suffix_tree > $search_out);
qx(./consenus >> $search_out);
#qx(rm sequence_temp);
#print "the result is stored in suffix_tree_search.out file\n";
qx(mv $search_out result/);
#qx(rm motif_temp1 motif_temp2);
  
exit 0;
