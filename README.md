# ofxFunctionalEasing

oF 0.9~

## How to use
// TODO:

### Type Definition

* using EasingFunction = function<void(float progress)>;
* using EasingCallback = function<void(const string &label)>;
* using TemplateFunction = float(*)(float progress, float start_value, float end_value);

### Constants

* ofxFunctional::defaultCallback = [](const string &){}

### APIs

#### Single easing

```cpp
string ofxFunctionalEasing(EasingFunction easing,
                           float duration,
                           const string &label = "",
                           EasingCallback callback = defaultCallback)

string ofxFunctionalEasing(EasingFunction easing,
                           float duration,
                           float delay,
                           const string &label = "",
                           EasingCallback callback = defaultCallback)
```

#### Group of easings

```cpp
string ofxFunctionalEasing(vector<EasingFunction> easings,
                           float duration,
                           const string &label = "",
                           EasingCallback callback = defaultCallback)

string ofxFunctionalEasing(vector<EasingFunction> easings,
                           float duration,
                           float delay,
                           const string &label = "",
                           EasingCallback callback = defaultCallback)
                           
string ofxFunctionalEasing(initializer_list<EasingFunction> easings,
                           float duration,
                           const string &label = "",
                           EasingCallback callback = defaultCallback)

string ofxFunctionalEasing(initializer_list<EasingFunction> easings,
                           float duration,
                           float delay,
                           const string &label = "",
                           EasingCallback callback = defaultCallback)
```

* easing(s) : easing function(s). parameter is normalized to [0.0, 1.0]. (i.e. elapsed time / duration)
* duration  : easing duration. [sec.]
* delay     : if this value is given, while delay time we do nothing. [sec.]
* label     : if you don't give label, we will give quasi-unique label automatically.
	* this label will be argument of callback.
* callback  : do nothing when finished if you don't give callback.

* return value : label was given (or quasi-unique label is asigned automatically).

please see ofxFunctionalEasingExample.

#### Create EasingFunction with Template Function

	template <typename T, typename std::enable_if<is_arithmetic<T>::value>::type *_=nullptr>
	EasingFunction EasingFromTemplate(ofxFunctional::TemplateFunction f, T &binded_value, T start_value, T end_value)

### Template Functions

#### Linear

* TemplateFunction ofxEasing::Linear

#### Quad

* TemplateFunction ofxEasing::InQuad
* TemplateFunction ofxEasing::OutQuad
* TemplateFunction ofxEasing::InOutQuad

#### Qubic

* TemplateFunction ofxEasing::InQubic
* TemplateFunction ofxEasing::OutQubic
* TemplateFunction ofxEasing::InOutQubic

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
