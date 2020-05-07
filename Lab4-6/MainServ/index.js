const express = require('express');
const bodyParser = require('body-parser');
const generator = require(`${__dirname}/models/GenTele/Generate`);
const sync = require(`${__dirname}/controllers/sync`)
const app = express();
app.use(bodyParser.json());

const PORT = 3001;


app.use('/api', require(`${__dirname}/controllers/api`));



app.listen(PORT, () =>{
    console.log(`Listening on http://localhost:${PORT}`);

    let minute = 1000 * 60;
    let timer = setInterval(() => {
        console.log(generator())
    }, minute);

})
.on('error', (e) => {console.log(`${URL} | error: ${e.code}`)});