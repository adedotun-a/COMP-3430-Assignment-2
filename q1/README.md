# COMP 3430 - Assignment 1 Adedotun Adeyemo 7784807 Readme

## How to compile

---

cd to the directory of the submission and run the command "make"

## How to run

---

Use the command "./q1 executable"
where executable is a proccess for example cat

## Design Choices

---

I use a buffer with a fixed size and assumes that all input recieved will be less than the buffer size. I attempted to check for the EOF from read however it does not end when using CTRL D, so CTRL C is used to end the code.
