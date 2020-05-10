const express = require('express');
const bodyParser = require('body-parser');
const request = require('request-promise');
const {DBid} = require(__dirname + '/config');

const app = express();
app.use(bodyParser.json());

const PORT = 3000 + Number(DBid);


app.use('/api', require(`${__dirname}/controllers/api`));



app.listen(PORT, () =>{
    console.log(`Listening on http://localhost:${PORT}`);

    let minute = 100 * 60;
    let timer = setInterval(() => {
        console.log('Generated value');

        request({
            method: 'POST',
            uri: `http://localhost:${PORT}/api/gen`,
        })
        .catch((err) => {
            console.log(`Request GENERATE ERROR: ${err}`);
        })
    }, 1 * minute);

    let timer2 = setInterval(() => {
        let serv = [];
        request({
            method: 'GET',
            uri: `http://localhost:${PORT}/api/service`,
            json: true
        })
        .then((response) => {
            console.log(response);
            response.forEach(element => {
                if(element.id != DBid){
                    serv.push(element.id);
                }
            });
            console.log(serv);

            serv.forEach(el => {
                let port = 3000 + Number(el);
                request({
                    method: 'GET',
                    uri: `http://localhost:${port}/api/watt/date/max/${el}`,
                    json: true
                })
                .then((response) => {
                    request({
                        method: 'GET',
                        uri: `http://localhost:${port}/api/watt/date/${el}`,
                        body: {date: response[0].date},
                        json: true
                    })
                    .then((response) => {
                        console.log('post');
                        if(response){
                            request({
                                method: 'POST',
                                uri: `http://localhost:${PORT}/api`,
                                json: true,
                                body: response
                            })
                            .catch((err) => {
                                console.log(`Request POST ERROR: ${err}`);
                            });
                        }
                    })
                    .catch((err) => {
                        console.log(`Request GET data FROM SERV ERROR: ${err}`);
                    });
                })
                .catch((err) => {
                    console.log(`Request GET max date FROM SERV ERROR: ${err}`);
                });
            });
        })
        .catch((err) => {
            console.log(`Request SERVICES ERROR: ${err}`);
        });
    }, 2*minute);

})
.on('error', (e) => {console.log(`${URL} | error: ${e.code}`)});