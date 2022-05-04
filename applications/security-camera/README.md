# Security Camera 

## Description 
This application decoddes MPEG encoded input video stream,
and performs an object detection task using the Tiny-YOLO-v2 model.


## Dependencies
libavcodec version 56

## Install Dependencies
In Ubuntu or Debian-based systems, run the following:

```
sudo apt-get update
sudo apt-get install ffmpeg libsm6 libxext6
sudo apt-get install libavutil-dev libavcodec-dev
```

## Python packages
* Python 3.6.9
* OpenCV-Python 4.5.5.64 
* Tensorflow 1.10.0 
* Numpy 1.14.5 
* Cython 0.29.28
* Darkflow 1.0.0
* Pathlib 1.0.1


## Install Python Dependencies:
Run the following commands:

```
pip install -r requirements.txt

git clone https://github.com/thtrieu/darkflow.git
cd darkflow
pip3 install --upgrade --user .
cd ..
``` 

## Download Tiny Yolo v2 Config and Weight File 
* tiny-yolo-voc.weights
      https://drive.google.com/drive/folders/0B1tW_VtY7onidEwyQ2FtQVplWEU
* tiny-yolo-voc.cfg
      https://github.com/thtrieu/darkflow/blob/master/cfg/tiny-yolo-voc.cfg
* yolo2_tiny_tf_weights.pickle
      https://drive.google.com/open?id=10J0CZ8ITNZpP24JwXrhr1kEAtro80k39

Once the files have been downloaded, run the following:

```
mv tiny-yolo-voc.cfg conf/
mv tiny-yolo-voc.weights weights/
mv yolo2_tiny_tf_weights.pickle weights/
```
 

## How to Build

To build this benchmark, run the following:

```make```


## How to Run

To run this benchmark, run the following command:

```./bin/security-camera```
