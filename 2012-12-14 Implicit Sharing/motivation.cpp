class Node {
	double lat_;
	double lon_;
public:
	Node() : lat_(0), lon_(0) {}
	Node(double lat, double lon) : lat_(lat), lon_(lon) {}
	void setLat(double lat) { lat_ = lat; }
	void setLon(double lon) { lon_ = lon; }
	double lat() { return lat_; }
	double lon() { return lon_; }
};

void doSomething(Node n) { /* ... */ }
void main(int argc, char ** argv) {
	Node n(52.2785658, 10.211247);
	doSomething(n);
}
