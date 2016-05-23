#ifndef SETUP_CFG
#define SETUP_CFG

// Channels as given be physical configuration of delay lines plugged into NIM-ECL-NIM unit
// Positron detector
#define CFG_CHANNEL_POS_CP2 16
#define CFG_CHANNEL_POS_U1_S 17
#define CFG_CHANNEL_POS_U2_S 18
#define CFG_CHANNEL_POS_V1_S 19
#define CFG_CHANNEL_POS_V2_S 20
#define CFG_CHANNEL_POS_W1_S 21
#define CFG_CHANNEL_POS_W2_S 22
// Electron detector
#define CFG_CHANNEL_ELEC_CP2 24
#define CFG_CHANNEL_ELEC_U1_S 27
#define CFG_CHANNEL_ELEC_U2_S 28
#define CFG_CHANNEL_ELEC_V1_S 25
#define CFG_CHANNEL_ELEC_V2_S 26
#define CFG_CHANNEL_ELEC_W1_S 30
#define CFG_CHANNEL_ELEC_W2_S 29

// External delays given by cabling from the detector potential divider to the NIM-ECL-NIM unit in ns NOT bins
// Positron detector
#define CFG_DELAY_POS_CP2 10
#define CFG_DELAY_POS_U1_S 10
#define CFG_DELAY_POS_U2_S 10
#define CFG_DELAY_POS_V1_S 10
#define CFG_DELAY_POS_V2_S 10
#define CFG_DELAY_POS_W1_S 10
#define CFG_DELAY_POS_W2_S 10
// 10 detector
#define CFG_DELAY_ELEC_CP2 16.2
#define CFG_DELAY_ELEC_U1_S 37.6
#define CFG_DELAY_ELEC_U2_S 37.6
#define CFG_DELAY_ELEC_V1_S 37.4
#define CFG_DELAY_ELEC_V2_S 37.2
#define CFG_DELAY_ELEC_W1_S 20.4
#define CFG_DELAY_ELEC_W2_S 18

//setting max and min positron times


//setting max and min ion times


#endif