#include "parameter-proxy.hh"
#include "../io/messages.hh"
#include "application.hh"

ParameterProxy::ParameterProxy(const clap_param_info &info, QObject *parent)
   : QObject(parent), _id(info.id), _name(info.name), _module(info.module),
     _value(info.default_value), _minValue(info.min_value), _maxValue(info.max_value),
     _defaultValue(info.default_value) {}

ParameterProxy::ParameterProxy(clap_id param_id, QObject *parent)
   : QObject(parent), _id(param_id) {}

void ParameterProxy::redefine(const clap_param_info &info) {
   Q_ASSERT(_id == info.id);

   if (_name != info.name) {
      _name = info.name;
      emit nameChanged();
   }

   if (_module != info.module) {
      _module = info.module;
      emit moduleChanged();
   }

   setMinValueFromPlugin(info.min_value);
   setMaxValueFromPlugin(info.max_value);
   setDefaultValueFromPlugin(info.default_value);

   setValueFromPlugin(std::min(_maxValue, std::max(_minValue, _value)));
}

void ParameterProxy::setIsAdjusting(bool isAdjusting) {
   if (isAdjusting == _isAdjusting)
      return;

   _isAdjusting = isAdjusting;
   clap_event_param_flags flags = CLAP_EVENT_PARAM_SHOULD_RECORD;
   flags |= isAdjusting ? CLAP_EVENT_PARAM_BEGIN_ADJUST : CLAP_EVENT_PARAM_END_ADJUST;
   clap::messages::AdjustRequest rq{_id, _value, flags};
   Application::instance().remoteChannel().sendRequestAsync(rq);
   emit isAdjustingChanged();
}

void ParameterProxy::setValueFromUI(double value) {
   value = clip(value);
   if (value == _value)
      return;

   _value = value;

   clap::messages::AdjustRequest rq{_id, _value, CLAP_EVENT_PARAM_SHOULD_RECORD};
   Application::instance().remoteChannel().sendRequestAsync(rq);
   emit valueChanged();
   emit finalValueChanged();
}

void ParameterProxy::setValueFromPlugin(double value) {
   if (_isAdjusting)
      return;

   value = clip(value);
   if (value == _value)
      return;

   _value = value;
   emit valueChanged();
   emit finalValueChanged();
}

void ParameterProxy::setModulationFromPlugin(double mod) {
   if (mod == _modulation)
      return;

   _modulation = mod;
   emit modulationChanged();
   emit finalValueChanged();
}

void ParameterProxy::setMinValueFromPlugin(double minValue) {
   if (minValue == _minValue)
      return;

   _minValue = minValue;
   emit minValueChanged();
}

void ParameterProxy::setMaxValueFromPlugin(double maxValue) {
   if (maxValue == _maxValue)
      return;

   _maxValue = maxValue;
   emit maxValueChanged();
}

void ParameterProxy::setDefaultValueFromPlugin(double defaultValue) {
   if (defaultValue == _defaultValue)
      return;

   _defaultValue = defaultValue;
   emit defaultValueChanged();
}

void ParameterProxy::setToDefault() {
   bool wasAdjusting = _isAdjusting;

   if (!wasAdjusting)
      setIsAdjusting(true);
   setValueFromUI(_defaultValue);
   if (!wasAdjusting)
      setIsAdjusting(false);
}

void ParameterProxy::setIsHovered(bool value) {
   if (_isHovered == value)
      return;
   _isHovered = value;
   emit isHoveredChanged();
}
