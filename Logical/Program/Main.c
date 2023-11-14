
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	fb_motor1.ke = 0.24;
	fb_motor1.Tm = 0.1;
	fb_motor1.u = 0;
	
	fb_motor2.ke = 0.24;
	fb_motor2.Tm = 0.1;
	fb_motor2.u = 0;
	
	fb_controller.k_p = 0.24*3;
	fb_controller.k_i = 7.2;
	fb_controller.max_abs_value = 24.0;
	fb_controller.dt = 0.01;
	fb_controller.integrator.dt=0.001;
	
	speed = 0;
	counter = 0;
	enable = 1;
	
}

void _CYCLIC ProgramCyclic(void)
{
	if(enable)
	{
		
		if(counter == 200)
		{
			speed = 50;
		}
		else if (counter == 400)
		{
			speed = 0;
			counter= 0;
		}
		
		counter++;
		
		fb_controller.e_in = speed - fb_motor1.w;
		FB_Controller(&fb_controller);
		
		fb_motor1.u = fb_controller.u_out;
		
		fb_motor2.u = speed * fb_motor2.ke;
		
		FB_Motor(&fb_motor1);
		FB_Motor(&fb_motor2);
		
		fb_integrator1.in = fb_motor1.w;
		FB_Integrator (&fb_integrator1);
	}
}

void _EXIT ProgramExit(void)
{

}

