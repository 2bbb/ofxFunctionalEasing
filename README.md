# ofxFunctionalEasing

oF 0.9~

## How to use
// TODO:

	string ofxFunctionalEasing(function<void(float progress)> easing,
	                           float duration,
	                           const string &label,
	                           const function<void(const string &label)> &callback)

	string ofxFunctionalEasing(function<void(float progress)> easing,
	                           float duration,
	                           float delay,
	                           const string &label,
	                           const function<void(const string &label)> &callback)

if you don't give label, we will give quasi-unique label automatically.

do nothing when finished if you don't give callback.

return value is label will give to callback (or quasi-unique label).

please see ofxFunctionalEasingExample.
	                           	                                
## Update history

### 2015/09/21 ver 0.0.1 release

* initial

## License

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd. / backspace.tokyo]
* 2bit@backspace.tokyo

## At the last

Please create a new issue if there is a problem.
And please throw a pull request if you have a cool idea!!
