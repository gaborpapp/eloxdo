#ifndef L3MESSAGE_H
#define L3MESSAGE_H

#define	ELO_PRESS	1  /* Flags in ELO_TOUCH status byte   */
#define	ELO_STREAM	2
#define	ELO_RELEASE	4

class L3Message
{
public:
	L3Message(double h_=0.0, double v_=0.0, int event_=-1):
		_h(h_),
		_v(v_),
		_event(event_)
	{}
	double _h, _v;
	int _event;
};

#endif // L3MESSAGE_H
