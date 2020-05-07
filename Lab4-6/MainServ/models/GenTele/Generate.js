const {DBid} = require(__dirname + '/../../config');


let dateNow = () => {
    let date = new Date();
    let yyyy = date.getFullYear();
    let mm = date.getMonth() < 9 ? "0" + (date.getMonth() + 1) : (date.getMonth() + 1); // getMonth() is zero-based
    let dd  = date.getDate() < 10 ? "0" + date.getDate() : date.getDate();
    let hh = date.getHours() < 10 ? "0" + date.getHours() : date.getHours();
    let min = date.getMinutes() < 10 ? "0" + date.getMinutes() : date.getMinutes();
    let ss = date.getSeconds() < 10 ? "0" + date.getSeconds() : date.getSeconds();
    
    return `${yyyy}-${mm}-${dd}-${hh}-${min}-${ss}`;
};

let randomInteger = (min, max) => {
    let rand = min + Math.random() * (max + 1 - min);
    return Math.floor(rand);
}

let generateTele = () => {
    return {
        id: DBid,
        watt: randomInteger(100, 300),
        date: dateNow()
    };
};

module.exports = generateTele;