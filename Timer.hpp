#pragma once
struct Timer
{
	// Member Variables
	float max_time = 0.f;		// Time to count
	float time = 0.f;			// Remaining Time
	bool time_up = false;		// End of Counting Flag
	bool is_counting = false;	// Is The Timer Able to count

	// Member Functions
	void update(float dt);	// Function to Update Time 
	void stop();
	void start();
	void restart();			// Reset And Start Counting
	void reset();			// Reset Without Counting
};

