class CheshireCat {
private:
	class Private {
		void hover();
		void smile();
		void setVisibility(bool visible);
	}
	Private * d;
public:
	CheshireCat();
	virtual ~CheshireCat();
	void hover();
	void smile();
	void appear();
	void disappear();
}
