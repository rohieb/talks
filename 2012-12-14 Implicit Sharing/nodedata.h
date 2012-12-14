#include <QSharedData>
class NodeData : QSharedData {
public:
	double lat_;
	double lon_;
	NodeData() : lat_(0), lon_(0) {}
	NodeData(const NodeData& o) : QSharedData(o),
		lat_(o.lat_), lon_(o.lon_) {}
	virtual ~NodeData() {}
};
