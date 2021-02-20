#ifndef _BITWISE_
#define _BITWISE_
#pragma once

/*
 * Here are a few nice tricks for 2's complement based machines
 * that I discovered a few months ago.
 */
IC	int		btwLowestBitMask(int v)		{	return (v & -v);	}
IC	DWORD	btwLowestBitMask(DWORD x)	{   return x & ~(x-1);	}

/* Ok, so now we are cooking on gass. Here we use this function for some */
/* rather useful utility functions */
IC	BOOL	btwIsPow2(int v)			{ return (btwLowestBitMask(v) == v); }
IC	BOOL	btwIsPow2(DWORD v)			{ return (btwLowestBitMask(v) == v); }

IC	int		btwPow2_Ceil(int v)
{
	int i = btwLowestBitMask(v);
	while(i < v) i <<= 1;
	return i;
}
IC	DWORD	btwPow2_Ceil(DWORD v)
{
	DWORD i = btwLowestBitMask(v);
	while(i < v) i <<= 1;
	return i;
}

// Couple more tricks 
// Counting number of nonzero bits for 8bit number: 

IC	BYTE	btwCount1(BYTE v)
{
	v = (v & 0x55) + ((v >> 1) & 0x55);
	v = (v & 0x33) + ((v >> 2) & 0x33);
	return (v & 0x0f) + ((v >> 4) & 0x0f);
}

//same for 32bit 
#define g31 0x49249249ul // = 0100_1001_0010_0100_1001_0010_0100_1001
#define g32 0x381c0e07ul // = 0011_1000_0001_1100_0000_1110_0000_0111
IC	DWORD	btwCount1(DWORD v)
{
	v = (v & g31) + ((v >> 1) & g31) + ((v >> 2) & g31);
	v = ((v + (v >> 3)) & g32) + ((v >> 6) & g32);
	return (v + (v >> 9) + (v >> 18) + (v >> 27)) & 0x3f;
}
#undef g31
#undef g32

#endif