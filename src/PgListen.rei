type t;

let make:
    (~user: string=?, ~host: string=?, ~database: string=?, ~password: string=?, ~port: int=?,
     ~sslCa: string=?, ~sslCert: string=?, ~sslKey: string=?, ~connectionString: string=?, unit)
    => t;

let connect: t => Js.Promise.t(unit);
let close: t => Js.Promise.t(unit);
let listenTo: (t, string) => Js.Promise.t(Js.Json.t);
let notify: (t, string, Js.Json.t) => Js.Promise.t(Js.Json.t);

let onError: (t, Js.Json.t => unit) => unit;
type notificationEvent = { channel: string, payload: Js.Json.t };
let onNotification: (t, notificationEvent => unit) => unit;
let on: (t, string, Js.Json.t => unit) => unit;
