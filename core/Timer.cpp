#include "Timer.h"

#include <GLFW/glfw3.h>

Timer::Timer()
	: m_StartTime(0.0), m_ElapsedTime(0.0)
{

}

void Timer::StartWatch()
{
	m_StartTime = glfwGetTime();
}

void Timer::StoptWatch()
{
	m_ElapsedTime = glfwGetTime() - m_StartTime;
}