function set_pin_value(pin, value) {
    var context = $jsapi.context();
    var options = {
        dataType: "json",
        headers: {
            "Content-Type": "application/json",
        },
        body: value
    };
    var response = $http.put("http://blynk-cloud.com/" + context.injector.TOKEN + "/update/" + pin, options);
}