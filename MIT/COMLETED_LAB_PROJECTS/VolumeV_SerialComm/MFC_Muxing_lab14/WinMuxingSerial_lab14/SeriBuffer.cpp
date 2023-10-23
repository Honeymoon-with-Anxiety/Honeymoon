// SeriBuffer.cpp: implementation of the CSeriBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mutexes.h"
#include "SeriBuffer.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSeriBuffer::CSeriBuffer()
{
	channel_storage = NULL;
	channel_iterator = NULL;
	current_channel =0;
	num_channels = 0;
	channel_sz = 0;
	channel_full=false;
}

CSeriBuffer::CSeriBuffer(size_t chanl_sz, size_t num_chnls)
{
	num_channels = num_chnls;
	channel_sz = chanl_sz;

	channel_storage = new std::deque<BYTE>[num_channels];

	channel_full=false;
	current_channel=0;
}


CSeriBuffer::~CSeriBuffer()
{
	delete [] channel_storage;
}

CSeriBuffer::initCSeriBuffer()
{
	for(size_t i =0;i<num_channels;i++)
		for(size_t j=0;j<channel_sz;j++)
		{
			//srand((unsigned)time( NULL ));
			channel_storage[i].push_front(((BYTE) rand())%255);
		}
}

void CSeriBuffer::insert(BYTE data,size_t chn)
{
	if(channel_storage[chn].size()<channel_sz)
	{
		channel_storage[chn].push_front(data);
	}
	else 
	{
		channel_full=true;
		channel_storage[chn]
			.erase(channel_storage[chn].end());

		channel_storage[chn].push_front(data);
	}
}

BYTE CSeriBuffer::GetData(size_t channel)
{
	
	if((channel>=0)&&(channel<num_channels))
	if(!channel_storage[channel].empty())
	{
		BYTE ret_val='x';
		ret_val = channel_storage[channel].back();
		channel_storage[channel].pop_back();
		return ret_val;
	}

	return 0;
}

void CSeriBuffer::next_channel()
{
	current_channel++;
	if(current_channel>=num_channels) current_channel=0;
}
