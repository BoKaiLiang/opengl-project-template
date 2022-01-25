#ifndef _TIME_H_
#define _TIME_H_

class Timer final
{
public:
	Timer();

	void StartWatch();
	void StoptWatch();

	inline double GetElapsedTime() const { return m_ElapsedTime; }

private:
	double m_StartTime;
	double m_ElapsedTime;
};

#endif // _TIME_H_