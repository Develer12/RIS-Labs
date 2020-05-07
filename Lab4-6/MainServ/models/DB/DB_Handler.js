const sql = require('mssql');

let connectionPool;
const config =
{
  user:'Develer12',
  password: 'admin',
  server:'DESKTOP-U4BLHC6', Database:'RISmain'
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

    getbyDate(date){
        return connectionPool.then(pool => pool.query(`${use} SELECT * FROM Watts where date = ${date}`));
    }

    getAll(){
        return connectionPool.then(pool => pool.query(`${use} SELECT * FROM Watts`));
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

module.exports = DB;
