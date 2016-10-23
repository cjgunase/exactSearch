use warnings;
use strict;
use File::Find;
use File::Basename;
use Data::Dumper;
use lib '/var/www/html/motif/modules/share/perl5';
use lib '/var/www/html/motif/modules/share/man/man3';
use Tie::Hash::Regex;
use File::Copy;
my %fasta_hash;
my $bgModel;
my $command;
tie %fasta_hash, 'Tie::Hash::Regex';

my %hash=();
my %args=@ARGV;
#my $direction = $args{'-dir'};
#my $cut = $args{'-cut'};
my $group = $args{'-group'};

my $species = $args{'-specis'};
#$species=~s/_/ /g;
#my @val = split(',',`grep "$species" ./speciesNametoIDs.csv`);
#my $organism_id = $val[1];
my $filename = $args{'-fn'};
my $email = $args{'-email'};
#my $geneIdList = $args{'-data'};

#my @geneIdList = split(" ",$geneIdList);


my $file = "biomart.fasta";  
my $removed = unlink($file);
print "Removed $removed file(s).\n";


	my $groupval = 0;
	 my $lookup;
	if($group eq 'D600'){
		$groupval = 600;
		$bgModel = "./sequences_down_600_bg/".$species.".bg";
		my $file="./sequences_down_600/".$species;
		qx(cp $file biomart.fasta);
		`chmod 777 biomart.fasta`;





	}elsif($group eq 'U1000'){
		$groupval = 1000;
		$bgModel = "./sequences_up_1000_bg/".$species.".bg";
		my $file="./sequences_up_1000/".$species;
		qx(cp $file biomart.fasta);
		`chmod 777 biomart.fasta`;

		
	}elsif($group eq 'U1500'){
		$groupval = 1500;
		$bgModel = "./sequences_up_1500_bg/".$species.".bg";
		my $file="./sequences_up_1500/".$species;
		qx(cp $file biomart.fasta);
		`chmod 777 biomart.fasta`;

	}elsif($group eq 'U2000'){
		$groupval = 2000;
		$bgModel = "./sequences_up_2000_bg/".$species.".bg";
		my $file="./sequences_up_2000/".$species;
		qx(cp $file biomart.fasta);
		`chmod 777 biomart.fasta`;

	
	}	





	if (index($filename, 'fasta') != -1) {

		if (-e "biomart.fasta") 
	{ 
    		`perl exactMatch.pl biomart.fasta $filename $email $groupval`;
		#`rm biomart.fasta`;
		#`rm $filename`;
#		`chmod 777 biomart.fasta_exact_match.txt`;
#		`perl sendEmail.pl $email biomart.fasta`;
		#`rm biomart.fasta_exact_match.out`;
	}




	}elsif(index($filename, 'ppm') != -1){
		qx(rm myfiles.zip);
		#`rm biomart.bg`;
		#`./CreateBackgroundModel -f biomart.fasta - b biomart.bg`;
		#`chmod 777 biomart.bg`;
		#`perl readPFM.pl $filename`;
		
		open(pfm,"$filename")or die "$!";
		my $w=0;
		my @filenames;
		while(<pfm>){
   
		    if(index($_, 'ID') != -1){
			my @val = split("=",$_);
			$val[1] =~ s/^\s+|\s+$//g;
			open(FILE,">$val[1]") or die "$!";
			print FILE "#INCLUSive Motif Model\n";
			print FILE "$_";
			push (@filenames,$val[1]);
			`chmod 777 $val[1]`;
		    }

		    if($w>0){
		        print FILE "$_";
		        $w=$w-1;
		    }

		    if(index($_, 'W') != -1){
			my @val= split("=",$_);
		        $w=$val[1];
			print FILE "$_";
		    } 


		}
		qx(mkdir motifMatrix);

		my $fn;
		foreach $fn (@filenames){
		        my $file="./".$fn;
		        move($file,"./motifMatrix");
		   }
		   $command = "perl matrixSearch.pl biomart.fasta $bgModel motifMatrix";
		qx(mkdir MotifLocator_result);
		qx($command);		
		#qx(perl matrixSearch.pl biomart.fasta biomart.bg motifMatrix);
		qx(zip -r myfiles.zip MotifLocator_result);
		qx(perl sendEmailPFM.pl $email);
		qx(rm -r MotifLocator_result);
		
		qx(rm -r motifMatrix);

	}







