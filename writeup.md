# **PID Controller Project**

The goals / steps of this project are the following:
* Understand how PID controller works and effect of each P/I/D component
* Implement PID Controller in C++


[//]: # (Image References)

[image1]: ./writeup_images/P_coefficient.png "P"
[image2]: ./writeup_images/D_coefficient.png "D"
[image3]: ./writeup_images/I_coefficient.png "I"
[image4]: ./writeup_images/final.png "Final"
[video1]: ./writeup_images/Final_Lap.mp4 "Video"



## Rubric Points
#### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/824/view) individually and describe how I addressed each point in my implementation.  


### Compiling
#### 1. Your code should compile.
I completed the project under Ubuntu bash on Windows 10. I didn't modify CMakeLists.txt and other configuration files, so follow below to compile the code.  

~~~sh
cd build
cmake ..
make
./pid
~~~

Then, launch Term 2 simulator.

### Implementation
#### 1. The PID procedure follows what was taught in the lessons.

As soon as the program starts, I initialize PID coefficients with `PID::Init()` function. And then, everytime simulator gives CTE value, I updated errors used for each PID component.   

I calculate steer angle with updated errors and return steer angle value to the simulator.

~~~cpp
pid.Init(0.15, 0.001, 5);
pid.UpdateError(cte);
steer_value= -pid.Kp * pid.p_error \
            - pid.Ki * pid.i_error \
            - pid.Kd * pid.d_error;
~~~

With CTE value, I update each of p_error, i_error and d_error. For proportional error(`p_error`), I just use CTE value itself. For integral error(`i_error`), I get cumulated CTE value by adding every CTE to i_error. For differential error(`d_error`), I get difference between previous CTE and present CTE.  

And for the last, I added class variable `total_error` to describe cumulated squared CTE value, and it is used to calculate average CTE value throughout the map.

~~~cpp
void PID::UpdateError(double cte) {
  double prev_error = p_error;
  i_error += cte;
  p_error = cte;
  d_error = cte - prev_error;

  total_error += (cte*cte);
} 
~~~


### Reflection
#### 1. Describe the effect each of the P, I, D components had in your implementation.  

On the straight road, the effect each of the PID is not distinguishable. Once curvy roads appear, I can tell the importance of PID controller.

With high P coeffient, the vehicle keeps driving zigzag, and falls out of the track. As seen in the graph below, when curvy road starts, the vehicle starts repeatedly turn left and right with high P. With low P, the vehicle drive relatively stable on the straigh road, but cannot react immediately to the sharp curve and gets out of track again.  

![image1]

For sharp curves, I need to add D-coefficient. As D coefficient increases, CTE at sharp curves gets acceptable range. With P coefficient 0.1 and D coefficient 5, the vehicle succeed to drive a lap around the track.  
![image2]  

However, I found out average CTE values are little bit larger than 0, so I decide to apply I coefficient to reduce systemetic bias.  

![image3]  

With too high I-coefficient, the vehicle turns too much at the start of the lap and falls out of the track. I tried to find proper I coefficient by decreasing I-value.   
  

#### 2. Describe how the final hyperparameters were chosen.

As stated above, I started to tune P coefficient, then D coefficient, lastly I value. Each coefficient starts with value 1 and each pair was compared with previous pairs. 
After I find some pairs which vehicle succeed to drive a lap around the track with, I tuned each parameter with smaller delta like 0.1 or 0.01. I used average CTE value for a lap to figure out the best coefficient values. Finally, I get `(0.13, 0.001, 5)`. The final CTE graph is as below.  

![image4]  

### Simulation
#### The vehicle must successfully drive a lap around the track.

And my final driving record is as below. (If not shown, please refer to `./writeup_images/Final_Lap.mp4`)  
![video1]  