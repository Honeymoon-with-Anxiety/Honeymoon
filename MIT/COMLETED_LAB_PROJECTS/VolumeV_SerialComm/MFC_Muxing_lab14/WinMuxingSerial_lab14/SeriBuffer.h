// SeriBuffer.h: interface for the CSeriBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include <deque>

#if !defined(AFX_SERIBUFFER_H__D0D3BB15_91BB_4EDF_8F1E_7BAE3CA59CCA__INCLUDED_)
#define AFX_SERIBUFFER_H__D0D3BB15_91BB_4EDF_8F1E_7BAE3CA59CCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//this class serves as the buffer for the data incoming
//from the MCU. This data is assumed to be muxed into a
//serial stream of bytes. It will be demultiplexed by this
//structure and each channel will be placed into its corresponding
//QUEUE. It is assumed that the data is streaming byte by byte
//as follows: channel 0, channel 1, ... channel n, and then channel 0
//again.
//


class CSeriBuffer  
{
public:
	CSeriBuffer();
	CSeriBuffer(size_t chnl_sz, size_t num_chnls);
	virtual ~CSeriBuffer();

	initCSeriBuffer();//initializes the datastructure with random #'s
	void insert(BYTE data,size_t chn);
	BYTE GetData(size_t channel);//returns the oldest element in the channels Q
	void next_channel();

	size_t num_channels;
	size_t channel_sz;		//size of channel
	std::deque<BYTE>* channel_storage; //stores the individual bytes as received from MCU
	size_t* channel_iterator; //keeps track of the next insertion point in each channel
	size_t current_channel;	  //currently inserting channel
	bool channel_full;		  //if there is a place to insert more data this member
							  //is false
};

#endif // !defined(AFX_SERIBUFFER_H__D0D3BB15_91BB_4EDF_8F1E_7BAE3CA59CCA__INCLUDED_)
