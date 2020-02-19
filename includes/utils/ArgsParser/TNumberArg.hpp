#ifndef TNUMBERARG_HPP_
#define TNUMBERARG_HPP_

#include <sstream>

#include "AInfoArg.hpp"
#include "ArgsParser.hpp"

// -- NumberArg template -------------------------------------------------------
template<typename T>
class NumberArg : public AInfoArg {
	public:
		NumberArg<T>(ArgsParser *argsParser, std::string const &name, ArgType::Enum const type,
			std::string const &longName, char shortName)
		: AInfoArg(argsParser, name, type, longName, shortName),
		_min(std::numeric_limits<T>::lowest()),
		_max(std::numeric_limits<T>::max()),
		_defaultV(static_cast<T>(0)),
		_value({static_cast<T>(0), false}) {
			// if positionnal argument
			if (!_required) {
				_value.second = true;  // enable default value
			}
		}

		virtual ~NumberArg<T>() {
		}

		NumberArg<T>(NumberArg<T> const &src) {
			*this = src;
		}

		NumberArg<T>	&operator=(NumberArg<T> const &rhs) {
			AInfoArg::operator=(rhs);
			if (this != &rhs) {
				_min = rhs._min;
				_max = rhs._max;
				_defaultV = rhs._defaultV;
				_value = rhs._value;
			}
			return *this;
		}

		virtual void print(std::ostream &out) const {
			AInfoArg::print(out);

			// print defaut int value
			if (!_required) {
				out << " " COLOR_L_VAL "default" LOG_COL_WHITE "=" COLOR_R_VAL <<
					_defaultV << LOG_COL_WHITE;
			}

			// print string min/max
			if (_min != std::numeric_limits<T>::lowest() ||
				_max != std::numeric_limits<T>::max()) {
				out << " " COLOR_L_VAL "range" LOG_COL_WHITE "=" COLOR_R_VAL "[";
				if (_min != std::numeric_limits<T>::lowest()) {
					out << std::fixed << std::setprecision(3) << _min;
				}
				out << ":";
				if (_max != std::numeric_limits<T>::max()) {
					out << std::fixed << std::setprecision(3) << _max;
				}
				out << "]" LOG_COL_WHITE;
			}

			out << ">";
		}

		// -- overide virtual parent members -----------------------------------

		// ---- only enabled for floating point --------------------------------
		AInfoArg	&setDefaultF(long double defaultV) {
			if (std::is_floating_point<T>::value) {
				_assertRange<long double>("setDefaultF", defaultV);
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultF(defaultV);
		};
		AInfoArg	&setMinF(long double min) {
			if (std::is_floating_point<T>::value) {
				_assertRange<long double>("setMinF", min);
				return _setMin(min);
			}
			return AInfoArg::setMinF(min);
		};
		AInfoArg	&setMaxF(long double max) {
			if (std::is_floating_point<T>::value) {
				_assertRange<long double>("setMaxF", max);
				return _setMax(max);
			}
			return AInfoArg::setMaxF(max);
		};
		// ---- only enabled for signed integral -------------------------------
		AInfoArg	&setDefaultI(int64_t defaultV) {
			if (std::is_integral<T>::value && std::is_signed<T>::value) {
				_assertRange<int64_t>("setDefaultI", defaultV);
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultI(defaultV);
		};
		AInfoArg	&setMinI(int64_t min) {
			if (std::is_integral<T>::value && std::is_signed<T>::value) {
				_assertRange<int64_t>("setMinI", min);
				return _setMin(min);
			}
			return AInfoArg::setMinI(min);
		};
		AInfoArg	&setMaxI(int64_t max) {
			if (std::is_integral<T>::value && std::is_signed<T>::value) {
				_assertRange<int64_t>("setMaxI", max);
				return _setMax(max);
			}
			return AInfoArg::setMaxI(max);
		};

		// ---- only enabled for unsigned integral -----------------------------
		AInfoArg	&setDefaultU(uint64_t defaultV) {
			if (std::is_unsigned<T>::value) {
				_assertRange<uint64_t>("setDefaultU", defaultV);
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultU(defaultV);
		};
		AInfoArg	&setMinU(uint64_t min) {
			if (std::is_unsigned<T>::value) {
				_assertRange<uint64_t>("setMinU", min);
				return _setMin(min);
			}
			return AInfoArg::setMinU(min);
		};
		AInfoArg	&setMaxU(uint64_t max) {
			if (std::is_unsigned<T>::value) {
				_assertRange<uint64_t>("setMaxU", max);
				return _setMax(max);
			}
			return AInfoArg::setMaxU(max);
		};

		// -- getters ----------------------------------------------------------
		T					getMin() const { return _min; }
		T					getMax() const { return _max; };
		std::pair<T, bool>	getVal() const { return _value; }

		template<typename U>
		void	saveVal(U val) {
			_assertRange<U>("parseArgs", val);
			_value = {static_cast<T>(val), true};
		}

		// convert the input string to T
		virtual void	setVal(std::string input);

	private:
		NumberArg<T>();

		// helper to test range value
		template<typename V>
		void	_assertRange(std::string const fName, V val, bool outOfRange = false) {
			if (val < static_cast<V>(_min) || val > static_cast<V>(_max) ||
				outOfRange) {
				std::stringstream strS;
				strS << "arg \"" << _name << "\": " << fName << "(): ";
				if (!outOfRange) {
					strS << val << " ";
				}
				strS << " out of range: [" << +_min << ":" << +_max << "]";
				throw AInfoArgError(strS.str().c_str());
			}
		}

		// -- templates to avoid code duplication ------------------------------
		AInfoArg	&_setDefault(T defaultV) {
			if (_required) {
				throw AInfoArgError(std::string("arg \"" + _name + "\": setDefault(): "
				"you can't set default value of positional arguments").c_str());
			}
			else if (defaultV < _min) {
				throw AInfoArgError(std::string("arg \"" + _name + "\": setDefault(): default:" +
					std::to_string(defaultV) + " < min:" + std::to_string(_min)).c_str());
			}
			else if (defaultV > _max) {
				throw AInfoArgError(std::string("arg \"" + _name + "\": setDefault(): default:" +
					std::to_string(defaultV) + " > max:" + std::to_string(_max)).c_str());
			}
			else {
				this->_defaultV = defaultV;
				_value = {defaultV, true};  // update _value accordingly
			}
			return *this;
		};

		AInfoArg	&_setMin(T min) {
			if (!_required && _defaultV < min) {
				throw AInfoArgError(std::string("arg \"" + _name + "\": setMin(): min:" +
					std::to_string(min) + " > default:" + std::to_string(_defaultV)).c_str());
			}
			else {
				this->_min = min;
			}
			return *this;
		};

		AInfoArg	&_setMax(T max) {
			if (!_required && _defaultV > max) {
				throw AInfoArgError(std::string("arg \"" + _name + "\": setMax(): max:" +
					std::to_string(max) + " < default:" + std::to_string(_defaultV)).c_str());
			}
			else {
				this->_max = max;
			}
			return *this;
		};


		T					_min;
		T					_max;
		T					_defaultV;
		std::pair<T, bool>	_value;
};


// -- convertVal template function definition and declaration ------------------
// uses specialization to manage conversion

// floating point specification
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
convertVal(NumberArg<T> *ref, std::string input) {
	long double val = std::stold(input);
	ref->template saveVal<long double>(val);
}

// signed integral specification
template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, void>::type
convertVal(NumberArg<T> *ref, std::string input) {
	int64_t	val = std::stoll(input);
	ref->template saveVal<int64_t>(val);
}

// unsigned integral specification
template <typename T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type
convertVal(NumberArg<T> *ref, std::string input) {
	// first cast input to double to detect out of range
	double	dVal = std::stod(input);
	if (dVal < 0 || dVal > std::numeric_limits<uint64_t>::max()) {
		throw AInfoArg::AInfoArgError("out of range input");
	}
	// reconvert again for precision
	uint64_t val = std::stoull(input);
	ref->template saveVal<uint64_t>(val);
}


// -- setVal definition --------------------------------------------------------
// we need to define setVal after convertVal declaration to avoid circular dependencies
template<typename T>
void	NumberArg<T>::setVal(std::string input) {
	try {
		convertVal<T>(this, input);
	}
	catch (const std::out_of_range &e) {
		_assertRange<T>("parseArgs", 0, true);
	}
	catch (const std::invalid_argument &e) {
		throw AInfoArgError(std::string("arg \"" + _name +
			"\": parseArgs(): failed to convert input \"" + input + "\"").c_str());
	}
}

#endif  // TNUMBERARG_HPP_
