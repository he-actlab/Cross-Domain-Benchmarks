# Video Sync 

## Description 
In this application, given a video file and a corresponding
subtitle text file, it synchronizes the subtitles with speech segments using
MPEG-decoding and Fast Fourier Transform to boost the speech-text pattern
matching process.


## Dependencies
libavcodec version 56


## Installing Dependencies
In Ubuntu or Debian-based systems, run the following:

```sudo apt-get install libavutil-dev libavcodec-dev``` 


## How to Build
To build this benchmark, run the following:

```make```


## How to Run

To run this benchmark, run the following command:

```./bin/video-sync```
