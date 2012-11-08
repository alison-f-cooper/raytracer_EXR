#!/usr/bin/perl

$| = 1;

$filename = $ARGV[0];
$outfile = $ARGV[1];

open (FILE, "<$filename" || die);

my @lines = <FILE>;

close FILE;

open (FILE2, ">$outfile" || die);

foreach $line (@lines)
{
	chomp($line);
	if($line =~ m/(g\s)(\w+)/)
	{
		print FILE2 ("#" . $2 . "\n");
	}
	elsif($line =~ m/(v )/)
	{
		print FILE2 ($line . "\n");
	}
	elsif($line =~ m/(f )(\d+)(\/)(\d+)(\s)(\d+)(\/)(\d+)(\s)(\d+)(\/)(\d+)/)
	{
		print FILE2 ($1 . $2 . $5 . $6 . $9 . $10 . "\n");
	}
}
close FILE2;
