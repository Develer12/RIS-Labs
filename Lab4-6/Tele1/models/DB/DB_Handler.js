const sql = require('mssql');
const {DBid} = require(__dirname + '/../../config');

let connectionPool;
const config =
{
  user:'Develer12',
  password: 'admin',
  server:'DESKTOP-U4BLHC6', Database:'RIS1'
};
let use = 'use RISmain;';

class DB {
    constructor()
    {
        connectionPool = new sql.ConnectionPool(config).connect().then(pool =>
        {
          console.log('Connected to MSSQL')
          return pool
        }).catch(err => console.log('Connection Failed: ', err));
    }

    getbyId(id){
        return connectionPool.then(pool => pool.query(`${use} SELECT * FROM Watts where id = ${id}`));
    }

    getService(){
        return connectionPool.then(pool => pool.query(`${use} SELECT DISTINCT id FROM Watts`));
    }

    getbyDate(date){
        return connectionPool.then(pool => pool.query(`${use} SELECT * FROM Watts where date = ${date}`));
    }

    getAll(){
        return connectionPool.then(pool => pool.query(`${use} SELECT * FROM Watts`));
    }

    insertNew(){
        return connectionPool
        .then(pool => pool.query(
        `
            ${use} INSERT INTO Watts values
            (${DBid}, ${randomInteger(100, 300)}, SYSDATETIMEOFFSET());
        `));
    }


    insert(body){
        return connectionPool.then(pool =>
        {
            const req = pool.request();
            let command = `${use} INSERT INTO Watts values `;
            body.forEach(fields => {
                command += '(';
                Object.keys(fields).forEach(field =>
                    {
                        let fieldType = Number.isInteger(fields[field]) ? sql.Int : sql.NVarChar;
                        req.input(field, fieldType, fields[field]);
                        command += `@${field},`;
                    });
                    command = command.replace(/.$/,") ,");
            });
            command = command.replace(/.$/,";");

            return req.query(command);
        });
    }
}

let randomInteger = (min, max) => {
    let rand = min + Math.random() * (max + 1 - min);
    return Math.floor(rand);
}


module.exports = DB;
