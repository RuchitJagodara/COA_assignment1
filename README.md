# ASR Model Training Instructions

## Overview

This documentation provides instructions for training an Automatic Speech Recognition (ASR) model using the Kaldi toolkit and SRILM for Gujarati.

## Prerequisites

Make sure you have the following installed:

- [Kaldi Toolkit](https://kaldi-asr.org/doc/install.html)
- [SRILM](http://www.speech.sri.com/projects/srilm/)
- [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads)
- [Vosk](https://alphacephei.com/vosk/) (Set up the vosk-server folder in the home directory.)
- [Phonetisaurus](https://github.com/AdolfVonKleist/Phonetisaurus)

## Steps for Training the ASR Model

### 1. Setting up the Model Directory Structure

First, download the data files and scripts from the following drive link: [Drive Link](https://drive.google.com/file/d/1L3i-CkvHCKRaKYad9WYS09lhR1CHPmA9/view?usp=drive_link) and then extract them.

### 2. Configure the env.sh

Check if env.sh is present and set it to the Language (change the value of LM_NAME, MODEL_NAME and G2P_NAME accordingly). Also, configure the nj (Number of Jobs) according to the system's CPU threads. Ideally, they should be at max 75% of the available threads. Set the LM_LAMBDA=1. This is set to 1 because we were required to build a generic model. This will make a new language model combining the main language model with the language model generated from the `extra.txt` present inside the db folder. But here we are assigning the weight of the main language model 100%. This is to maintain the generic nature of the model.

### 3. Check the Data

Check if the audio files are present in `[db/audio_data/gu_test/speaker_01]`. Also, make sure to check these files: `text, spk2utt, utt2spk, wav.scp` present inside the `data/train` and `data/test`.

### 4. Training the G2P Model

Inside the `db/gu-g2p` folder, run the following command to build the g2p model files, i.e., the .fst file

```bash
./build.sh
```

### 5. Training the Model

Now inside the root directory of the folder, run the bash script `run.sh` with the following command

```bash
./run.sh
```

### 6. After the Training is Complete

To deploy the model, first,to copy the model files to a folder, make a folder with the name whatever you want (in my case, I used gu_test) and now after making this folder make two folders named build and logs in that folder (i.e., gu_test folder). After doing so, open the `export_result.py` and change paths accordingly in the script. After doing so, run the script like below

```bash
python3 export_result.py gu_test
```

Here, in place of gu_test, it will be your model name, whatever you specified in which you have the build and logs folder.

After doing these steps, go to your `vosk-server/websocket` directory, and then in this directory open a terminal and then run the below script

```bash
python3 asr_server.py {PATH_TO_YOUR_BUILD_FOLDER}
```

Replace {PATH_TO_YOUR_BUILD_FOLDER} with your path to your build folder, and after this open a new terminal and then run the script `test.py` to run the model for your audio data.

## Extra Details

In the `run_tdnn.sh` script, I adjusted the value of epochs from 18 to 29 and modified the learning rate from 0.0001 to 0.0003. Additionally, I changed the ngram model order from 3 to 4 in the `run.sh` script. To avoid using the server's provided data, I commented out the s3cmd commands in both `run.sh` and `train_dict.sh` scripts, which were responsible for downloading files such as audio files, text, wav.scp, spk2utt, utt2spk, and more. These files were deemed incorrect, as we previously discussed, making them unsuitable for use. Consequently, I removed that section and also commented out the commands responsible for deleting these files whenever the `run.sh` command is executed. Due to the absence of a dedicated server for running our models, all tasks had to be performed on our local machine. This necessitated splitting a large 10 GB text file for the ngram command into parts. Subsequently, I created separate language models for each part and then merged them. It's worth noting that this process may have introduced some loss in accuracy.
# COA_assignment1
