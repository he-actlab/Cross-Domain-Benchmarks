# Cross Domain Multi-Acceleration Benchmarks #

FPGA-based domain-specific accelerators are increasingly becoming popular, but
currently there is a lack of systems support to utilize multiple accelerators 
across various application domains. Moreoever, currently there does not exist a
widely established benchmark suite that can be used to measure the benefits of
cross-domain multi-acceleration. To address this issue, we provide a benchmark
suite that consists of six real-life applications ranging from deep brain
stimulation, film captioning, medical imaging, and more. This benchmark suite is
developed at the Alternative Computing Technologies (ACT) Laboratory, University
of California, San Diego. 


## Applications ##

1. ** Memory Enhance [DSP, Data Analytics, Optimized Control] **: In this application, brain electrophysiological activity is
collected in real-time and passed through Fast Fourier Transform. Then, logistic
regression is used to decode and classify the signals to be used as biomarkers.
Lastly, Model Predictive Control is used configure the synthesized signals
depending on the classification output from the previous step. This pipeline can
be executed repeatedly to enhance memory capacity of small lab rats.

2. ** Robot Explorer [Robotics, Computer Vision] **: This application consists of a four-sheeled autonomous robot
equipped with a Kinect sesnsor to navigate its route through small, narrow
tunnels using the Model Predictive Control algorithm. Furthermore, it 
reconstructs a 3D map of the surrounding environment using the KinectFusion 
algorithm. 

3. ** Video Sync [DSP] **: In this application, given a video file and a corresponding
subtitle text file, it synchronizes the subtitles with speech segments using
MPEG-decoding and Fast Fourier Transform to boost the speech-text pattern
matching process.

4. ** Stock Market [Data Analytics, Finance] **: This application performs a sentiment analysis on news article
texts using logistic regression, and uses Black-Scholes to predict call option
pricing.

5. ** Leukocyte [Computer Vision] **: This application detects leukocytes from video microscopy of blood
vessels, where detection in the frame is done via Gradient Inverse Coefficient
of Variation scores, and leukocytes are detected via Motion Gradient Vector Flow
matrix.

6. ** Security Camera [Deep Learning, DSP] **: This application decoddes MPEG encoded input video stream,
and performs an object detection task using the Tiny-YOLO-v2 model.


## System Requirements ##

This benchmark suite requires the following systen environment parameters and
tools in order to succesfully compile and run.

* Ubuntu 16.04.5 LTS (Xenial Xerus) or newer
* gcc (and g++) version 5.4.0
* CMake version 3.5.1 or newer 
* Python version 2.7 or newer
* LAPACK version 3.6.0
* LAPACKE version 3.6.0


## Build and Run Instructions ##

We provide two options to build the benchmark suite: you can either build all
the benchmark applications at once, or build each benchmark application
individually. To build all applications at once, we provide a utility script
`build_all.sh` located in `scripts/` directory. You can simply run the script
like so: `./scripts/build_all.sh`. If you would like to build each benchmark
individually, go to its respective directory under `applications/` and follow 
the build instructions on the README file. 

To run the benchmarks, go to each benchmark application directory and follow the
directions on the respective README file.
