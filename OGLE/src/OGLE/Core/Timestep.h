#pragma once

namespace OGLE {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			:m_Time(time){}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time; }
	private:
		float m_Time;
	};
}