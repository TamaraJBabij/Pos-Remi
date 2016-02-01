#ifndef HIT_H
#define HIT_H

/*
	Enum for the different channels in the experiment
*/
enum ChannelID
{
	ChannelID_mcp,
	ChannelID_x1,
	ChannelID_x2,
	ChannelID_y1,
	ChannelID_y2,
	ChannelID_z1,
	ChannelID_z2
};

enum DetectorID
{
    DetectorID_pos,
    DetectorID_neg
};

/*
	1 datum from the experiment
*/

struct Hit
{
    ChannelID channel;
    DetectorID detector;
    Int_t bins;
    double time;
};

#endif
