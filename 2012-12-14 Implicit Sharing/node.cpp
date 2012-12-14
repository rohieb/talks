#include "nodedata.h"
#include <QSharedDataPointer>
class Node {
	QSharedDataPointer<NodeData> d;
public:
	Node() {}
	Node(double lat, double lon) {
		d = new NodeData;
		d->lat_ = lat;
		d->lon_ = lon;
	}
	Node(const Node& o) : d(o.d) {}

	void setLat(double lat) { d->lat_ = lat; }
	void setLon(double lon) { d->lon_ = lon; }
	double lat() { return d->lat_; }
	double lon() { return d->lon_; }
};

