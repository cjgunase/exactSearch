use Data::Dumper;
#!/usr/bin/perl
use strict;
use warnings;
use lib '/opt/BioMart/lib'; #Set this to path where you installed biomart-perl
use BioMart::Initializer;
use BioMart::Query;
use BioMart::QueryRunner;

my %args=@ARGV;
my $direction   = $args{'-dir'};
my $upstream    = $args{'-cut'};
my $organism_id = $args{'-sid'};
my $filename    = $args{'-fn'};

    


        my @geneIdList=`cut -f1 temp.txt`;
        $hash{$organism_id}=\@geneIdList;
        #my $organism_id = "$file[1]\n";
        my @transcript_name_filter = @{$hash{$file[1]}};
        
        
        #print Dumper \@transcript_name_filter;
        #print $organism_id="$file[1]";
        
        
        #my $confFile = "/opt/BioMart/conf/apiExampleRegistry.xml"; #Set this to path where you downloaded registry file
        my $confFile = "/opt/BioMart/conf/pyto.xml"; #Set this to path where you downloaded registry file
        my $tempfile = "biomart_query_temp.txt";
        
        #Note: change action to 'clean' if you wish to start a fresh configuration
        #Set to 'cached' if you want to skip configuration step on subsequent runs from the same registry
        my $action='cached';
        my $initializer = BioMart::Initializer->new('registryFile'=>$confFile, 'action'=>$action);
        my $registry = $initializer->getRegistry;
        my $query = BioMart::Query->new('registry'=>$registry,'virtualSchemaName'=>'default');
        
        $query->setDataset("phytozome");

if($direction=="up"){

        $query->addFilter("upstream_flank", [$upstream]);
}elsif($direction=="down"){
    $query->addFilter("downstream_flank", [$upstream]);

}
        $query->addFilter("organism_id", [$organism_id]);
        #$query->addFilter("transcript_name_filter", ["Aquca_001_00001.1"]);
        $query->addFilter("transcript_name_filter", [@transcript_name_filter]);
        
        $query->addAttribute("gene_name1");
        $query->addAttribute("transcript_name1");
        $query->addAttribute("coding_gene_flank");
        $query->formatter("FASTA");
        
        
        open (BIOMART_OUT, ">./seq.fasta") or die "Can't open file for write\n";
        my $query_runner = BioMart::QueryRunner->new();
        $query_runner->uniqueRowsOnly(1); #to obtain unique rows only
        $query_runner->execute($query);
        $query_runner->printResults(\*BIOMART_OUT);
	close(BIOMART_OUT);
        #exit;
        

    
    
    









