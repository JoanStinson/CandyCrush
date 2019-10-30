#ifndef _MODULE_H_
#define _MODULE_H_
#include "Globals.h"

class Application;

class Module {
public:
	Module(bool active = true) : active(active) {}
	virtual ~Module() {}

	bool IsEnabled() const {
		return active;
	}

	bool Enable() {
		return !active ? active = Start() : true;
	}

	bool Disable() {
		return active ? active = !CleanUp() : true;
	}

	virtual bool Init() {
		return true;
	}

	virtual bool Start() {
		return true;
	}

	virtual update_status PreUpdate() {
		return UPDATE_CONTINUE;
	}

	virtual update_status Update() {
		return UPDATE_CONTINUE;
	}

	virtual update_status LateUpdate() {
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate() {
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() {
		return true;
	}

private:
	bool active = true;
};

#endif 