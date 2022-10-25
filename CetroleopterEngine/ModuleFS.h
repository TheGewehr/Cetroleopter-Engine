#ifndef _MODULE_FS_H_
#define _MODULE_FS_H_

#include "Application.h"
#include "Module.h"

class ModuleFS : public Module
{
public:
	ModuleFS(bool start_enabled = true);
	~ModuleFS();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

public:
	

};

#endif // !_MODULE_FS_H_