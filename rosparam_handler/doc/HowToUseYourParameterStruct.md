# How to Use Your Parameter Struct
**Description**: This tutorial will familiarize you with how you can use the autogenerated parameter structs in your nodes.
**Tutorial Level**: INTERMEDIATE

## Generated files
When creating params files as described in [How to write your first .params file](HowToWriteYourFirstParamsFile.md), you will end up with the following two files:
- *'include/rosparam_tutorials/TutorialParameters.h'*
- *'include/rosparam_tutorials/TutorialConfig.h'*

The '<name>Parameters.h' file will hold a struct called `<name>Parameters`.  
The '<name>Config.h' file will hold the normal dynamic_reconfigure Config struct.

For your code it is enough to include the \*Parameters.h file, e.g.

```cpp
#include "rosparam_tutorials/TutorialParameters.h"
```

You can now add an instance of the parameter struct to your class:

```cpp
rosparam_tutorials::TutorialParameters params_;
```

## Initializing the struct.
When initializing your node, the params struct must be initialized with a private NodeHandle.

The call to `fromParamServer()` will take care of getting all parameter values from the parameter server, checking their type, and checking that a default value is set, if you haven't provided one on your own. If you have specified a default value, but the parameter is not yet present on the parameter server, it will be set. When min and max values are specified, these bounds will be checked as well.

```cpp
MyNodeClass::MyNodeClass()
  : params_{ros::NodeHandle("~")}
{
  params_.fromParamServer();
}
```

If you do not use a class (which you should do though in my opinion), you can create it like so:
```cpp
rosparam_tutorials::TutorialParameters params_{ros::NodeHandle("~")}
params_.fromParamServer();
```
Note: If you have set the logger level for your node to debug, you will get information on which values have been retrieved.  
Note: If you use nodelets, you have to use the `getPrivateNodeHandle()` function instead.

## Using dynamic_reconfigure
Your dynamic_reconfigure callback can now look as simple as:
```cpp
void reconfigureRequest(TutorialConfig& config, uint32_t level) {
    params_.fromConfig(config);
}
```
This will update all values that were specified as configurable. At the same time, it assures that all dynamic_reconfigure parameters live in the same namespace as those on the parameter server to avoid problems with redundant parameters.

Conversely, you can update the parameter on the dynamic_reconfigure server so that it
better reflects the state of your node:
```cpp
TutorialConfig config;
params_.toConfig(config);

dyn_reconf_mut_.lock();
dyn_reconf_srv_.updateConfig(config);
dyn_reconf_mut_.unlock();
```

You can find a running version of this example code in the [rosparam_handler_tutorial](https://github.com/cbandera/rosparam_handler_tutorial)-Repository

## Setting parameters on the server
If you change your parameters at runtime from within the code, you can upload the current state of the parameters with
```cpp
params_.toParamServer();
```
This will set all non-const parameters with their current value on the ros parameter server.

## Setting parameters at launch time
If you want to run your node with parameters other then the default parameters, then they have to be set on the parameter server before the node starts.
To ease the burden of setting all parameters one after the other, roslaunch has the [rosparam](http://wiki.ros.org/roslaunch/XML/rosparam) argument to load a YAML file containing a whole set of key value pairs.
Rosparam handler provides a script, to automatically generates a YAML file for you to use. Calling it will generate a file in your current directory.
```sh
rosrun rosparam_handler generate_yaml <path/to/Tutorial.params>
```

## Python
All your parameters are fully available in python nodes as well. Just import the parameter file:
```python
from rosparam_tutorials.param.TutorialParameters import TutorialParameters
```

Unlike in C++, the call to fromParamServer is not necessary:
```python
self.params = TutorialParameters()
```

And a dynamic_reconfigure callback might look like that:
```python
def reconfigure_callback(self, config, level):
    self.params.from_config(config)
    print("Parameter dummy changed to {}".format(self.params.dummy))
```

And a call to set the parameters on the server will look like this:
```python
self.params.to_param_server
```