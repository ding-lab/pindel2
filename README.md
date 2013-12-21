# Pindel

## Compiling 

To compile Pindel you need GNU Make, GCC and cppcheck and python. Usually they 
are already installed on Linux. On the Mac you will need to install XCode (3 or
higher), the latest version can be downloaded from the Mac App Store. cppcheck 
can be installed with Fink, MacPorts or Homebrew, where homebrew is more
convenient if you don't need to install other software from source.

Pindel requires samtools; you can download the latest version of samtools from
[the Samtools Sourceforge site](http://sourceforge.net/projects/samtools/files/). 
You need to extract and build samtools before you compile Pindel. Refer to the 
documentation of samtools for the requirements to build samtools.

If you make the Pindel project the first time, it will create a `Makefile.local`.
It will try to be smart and generate this file with the correct location of
samtools if you specify it on the make commandline.

    make SAMTOOLS=~/samtools-0.1.18

The `Makefile.local` also includes a couple of options for the different tests.
The `*_TIME` options define the max execution time for the jobs in the acceptance
tests, if they are exceeded the acceptance tests will fail.

The `THREADS` option defines the number of threads used in the functional tests,
this should be at least 2, it is recommended to match the number of cores in
your system to get the fastest execution time.


##Usage

Demonstration of how pindel can be used
 
To see all options of pindel, run pindel without any arguments, such as: 
<pindel_directory>/pindel
 
To run Pindel on a BAM-file, use the following command: 
    
    <pindel_directory>/pindel -i <bam_config_file> -f <reference.fa> -o <output_prefix> -c <name_of_chromosome/ALL>

Note that the bam-files must have been indexed in advance with samtools index 
 
Finally, one can run pindel on txt files out of bam-files created with bam2pindel. This option is not strictly needed as versions of pindel since 0.2.0 can read BAM files directly, this comparison of an actual tumor sample to its normal control gives an indication of Pindel\'s capabilities in research and clinical settings.
    
    <pindel_directory/pindel -p <pindel_input_file> -f <reference.fa> -o <output_prefix> -c <name_of_chromosome/ALL>
 
If you want to have the indel calls in vcf format, you can use the pindel to vcfconverter pindel2vcf;
    
    <pindel_directory>/pindel2vcf -r <reference.fa> -R <name_of_reference> -d <date_of_reference> -p <pindel_output_file>
 

##Contact

Please contact Beifang Niu by bniu@genome.wustl.edu and Kai Ye by kye@genome.wustl.edu if you have any questions.

