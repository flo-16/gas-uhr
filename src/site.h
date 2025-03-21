#ifndef SITE_H
#define SITE_H

class Site {
	private:
		String content;
	public:
		Site();
		String get() const { return content; }
};

Site::Site() {
	content = R"====(
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Gas Zähler</title>
    <style>
    body { background-color: #000; justify-content: center; align-items: center; }
        .container {
            width: 300px;
            height: 360px;
            background-color: #ccc;
            border: 2px solid black; border-radius: 10px; 
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: flex-start;
            padding: 30px;
            box-sizing: border-box;
        }

        .title {
            width: 100%;
            text-align: center; background-color: #ced;
            border: 2px solid black; border-radius: 7px;
            padding: 5px;
            font-weight: bold;
            margin-bottom: 10px;
        }

        .numbers {
            display: flex;
            gap: 5px;;
            flex-wrap: wrap;
            justify-content: center;
        }

        .number {
            font-family: Tahoma, Verdana, sans-serif;
            font-weight: bold;
            width: 18px;
            height: 30px; background-color: #6d893d;
            border: 1px solid black; border-radius: 5px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 18px;
        }
        .ticker {
            font-family: Tahoma, Verdana, sans-serif;
            font-weight: bold;
            color: #ffffff;
            cursor: pointer;
            width: 18px;
            height: 20px; background-color: #eee;
            border: 2px solid black; border-radius: 5px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 18px;
        }

        .komma {
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 25px;
        }

        .off { visibility: hidden; }
        .pointer { cursor: pointer; }
        .white { color: #ffffff; }
        .gold { color: #ffd700; }
        .plus { background-color: #228b22; }
        .minus { background-color: #ff0000; }
        .fs24 { font-size: 24px; }
        .fs18 {font-size: 18px; font-weight: normal }
        .padd { margin-top: 8px; padding: 10px; border: 1px solid black; border-radius: 3px; background-color: #aaaaaa; }
    </style>
    <script>
        const _WAITTIME = 1000;

        class GAZ {
            constructor() {
                this.digits = 7;
                this.actValue = 0;
                this.maxValue = 10000000;
                this.isEdit = false;
                this.timerCtrl = null;
                this.numberList = document.getElementsByClassName("number");
                this.tickerList = document.getElementsByClassName("ticker");
                Array.prototype.forEach.call(this.tickerList, (item, index) => {
                    item.addEventListener("click", () => { this.update(index); })
                })
                document.getElementById("button").addEventListener("click", () => { this.job() })
            } 
            view() {
                const tmp = (this.actValue + this.maxValue).toString();
                Array.prototype.forEach.call(tmp.substring(1), (item, index) => {
                    this.numberList[index].textContent = item;
                })
            }
            add(v) {    
                const tmp = this.actValue + v;
                if((tmp < this.maxValue) && (tmp >= 0)) {
                    this.actValue = tmp;
                    this.view();
                }
            }
            update(ind) {
                const operand = Math.floor(ind/this.digits);
                const weight = ind % this.digits;
                let delta = 10 ** (this.digits - weight - 1);
                if(operand) { delta *= -1;}
                this.add(delta);
            }
            getCounter() {
                fetch("/get?poll")    
                .then(res => res.json())
                .then(data => {
                    this.actValue = data.value;
                    this.view();
                })
                .catch(err => {console.log(err)});
            }
            setConter() {
                fetch("/get?cont=" + this.actValue)
                .then(res => res.text())
                .then(data => {console.log(data)})
                .catch(err => console.log(err));
            }
            job() {
                this.isEdit = !this.isEdit;
                if(this.isEdit) {
                    if(this.timerCtrl) {
                        window.clearInterval(this.timerCtrl);
                        this.timerCtrl = null;
                    }
                    document.getElementById("edit").style.visibility = "visible";
                } else {
                    document.getElementById("edit").style.visibility = "hidden";
                    this.setConter();
                    this.timerCtrl = window.setInterval( () => { this.getCounter();}, _WAITTIME)
                }
            }
            init() {
                this.getCounter();
                this.timerCtrl = window.setInterval( () => { this.getCounter(); }, _WAITTIME )
            }
        }

        window.onload = () => {
            const gaz = new GAZ();
            gaz.init();
        }
    </script>
</head>
<body>
    <div class="container">
        <div class="title fs24">GAS Zähler</div>
        <div class="title fs18">Aktueller Zählerstand in m³</div>
        <div class="numbers padd">
            <div class="number white"></div>
            <div class="number white"></div>
            <div class="number white"></div>
            <div class="number white"></div>
            <div class="number white"></div>
            <div class="komma">,</div>
            <div class="number gold"></div>
            <div class="number gold"></div>
        </div>
        <p></p>
        <div id="button" class="title fs18 pointer">Zählerstand setzen</div>
        <div id="edit" class="off">
            <div class="numbers">
                <div class="ticker plus">+</div>
                <div class="ticker plus">+</div>
                <div class="ticker plus">+</div>
                <div class="ticker plus">+</div>
                <div class="ticker plus">+</div>
                <div class="komma">,</div>
                <div class="ticker plus">+</div>
                <div class="ticker plus">+</div>
                <div class="m">  </div> 
            </div>  
            <div class="numbers">
                <div class="ticker minus">-</div>
                <div class="ticker minus">-</div>
                <div class="ticker minus">-</div>
                <div class="ticker minus">-</div>
                <div class="ticker minus">-</div>
                <div class="komma">,</div>
                <div class="ticker minus">-</div>
                <div class="ticker minus">-</div>
                <div class="m">  </div> 
            </div>
        </div>
    </div>
</body>
</html>

)====";
}

#endif