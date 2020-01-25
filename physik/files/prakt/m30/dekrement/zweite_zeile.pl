#!/bin/perl
#
# extracts every second line from given textfile
#
$infile="schwachged.data";
$infile_odd=$infile.".odd";
$infile_even=$infile.".even";
open(IN, "<$infile");
open(ODD, ">$infile_odd");
open(EV, ">$infile_even");
@infile = <IN>;
$n = 0;
foreach(@infile){
	if($n%2 == 1){
		print ODD "$_";
		print $_;
	}
	else{
		print EV "$_";
		print $_;
	}
	$n++;
}
print "done";
close IN;
close ODD;
close EV;
