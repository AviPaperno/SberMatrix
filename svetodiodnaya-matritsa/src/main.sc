require: zenflow.sc
  module = sys.zfl-common

require: slotfilling/slotFilling.sc
    module = sys.zb-common
  
require: js/blynk.js


theme: /
    state: EnableColor
        intent!: /EnableColor
        script:
            set_pin_value("V0",$parseTree._color);
        a: Готово
    state: Blink
        intent!: /Blink
        script:
             set_pin_value("V1",["1"]);
        a: Готово

    state: StopBlink
        intent!: /StopBlink
        script:
            set_pin_value("V1",["0"]);
        a: Готово

    state: Off
        intent!: /Off
        script:
            set_pin_value("V1",["0"]);
            set_pin_value("V0",["0","0","0"]);
        a: Готово

    state: ChangeImage
        intent!: /ChangeImage
        script:
            set_pin_value("V2",[$parseTree._image]);
        a: Готово

    state: Test
        q!: тест
        script:
                var dst = {
                dishId: "123",
                quantity: "1",
                };
                function getDishFromState(state) {
                        state = state || getState();
                        return new function() {
                        this.id = state.dishId;
                        this.quantity = state.quantity;
                        this.toppings = state.toppingIds || [];
                        this.type = "dish";
                        this.hasToppings = this.toppings.length > 0;
                    }
                }
                $temp.value = getDishFromState(dst);
                
            
        a: {{JSON.stringify($temp.value)}}

    state: Fallback
        event!: noMatch
        a: Вы сказали: {{$parseTree.text}}
        