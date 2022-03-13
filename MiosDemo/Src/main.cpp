#include "MioGE.h"
class SandBox : public miosGE::Application {
public:
	SandBox() {};
	~SandBox() {};

};
miosGE::Application* miosGE::CreateApplication() {
	return new SandBox();
}