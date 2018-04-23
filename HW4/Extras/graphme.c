#include<math.h>
#include<stdio.h>




#define shape 's'




double triangle_gen(double amplitude, double time, double wave_period);
double sin_gen(double amplitude, double time, double wave_period);



int main()
{

    double wave_period = 0;             //Seconds per wave
    double duration = 0;                //Duration of the trajectory
    double samp = 1000.;                //Samples per second
    double time = 0;                    //Time stamp


    if (shape == 't')
    {
        wave_period = 1.0/5.0;
        duration = wave_period;
    }
    else if (shape == 's')
    {
        wave_period = 1.0/10.0;
        duration = wave_period;
    }
    else
    {
        printf("arg invalid");
        return 1;
    }

    double numsamps = samp * duration;  //Total Samples
    double pointarray[(int)numsamps];
    double timearray[(int)numsamps];

    for(int i=0; i<(int)numsamps; i++)
    {
        if (shape == 't')
            pointarray[i] = triangle_gen(3.3, time, wave_period);
        else if (shape == 's')
            pointarray[i] = sin_gen(1.65, time, wave_period);
        timearray[i] = time;
        time = time + 1.0/samp;          //Seconds per sample
    }

    for(int i=0; i<(int)numsamps; i++)
        printf("%f \n", pointarray[i]);

    return 0;
}

double triangle_gen(double amplitude, double time, double wave_period)
{
    return (amplitude * 2/wave_period * (wave_period/2 - fabs(fmod(time, wave_period) - wave_period/2)));
}



double sin_gen(double amplitude, double time, double wave_period)
{
    float phase = 0.0;
    return amplitude * sin(2.0 * 3.14159 * 1.0/wave_period * time + phase) + 1.65;
}
