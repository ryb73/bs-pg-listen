type opts;
[@bs.obj]
external opts:
    (~user: string=?, ~host: string=?, ~database: string=?, ~password: string=?,
     ~port: int=?, ~connectionString: string=?, unit) => opts = "";

type t;
[@bs.module] external make: opts => t = "pg-listen";
let make =
    (~user=?, ~host=?, ~database=?, ~password=?, ~port=?, ~connectionString=?, ()) =>
        opts(~user?, ~host?, ~database?, ~password?, ~port?, ~connectionString?, ())
        |> make;

[@bs.send] external connect: t => Js.Promise.t(unit) = "";
[@bs.send] external close: t => Js.Promise.t(unit) = "";
[@bs.send] external listenTo: t => string => Js.Promise.t(Js.Json.t) = "";
[@bs.send] external notify: t => string => Js.Json.t => Js.Promise.t(Js.Json.t) = "";

type events;
[@bs.get] external events: t => events = "";
type notifications;
[@bs.get] external notifications: t => notifications = "";

[@bs.send]
external onError: (events, [@bs.as "error"] _, (Js.Json.t => unit)) => unit = "on";
let onError = (subscriber) => events(subscriber) |> onError;

[@bs.send]
external onNotification:
    (events, [@bs.as "notification"] _, (Js.Json.t => unit)) => unit = "on";
[@decco] type notificationEvent = { channel: string, payload: Js.Json.t };
let onNotification = (subscriber, cb) => {
    onNotification(events(subscriber), result =>
        notificationEvent_decode(result)
        |> Belt.Result.getExn
        |> cb
    );

};

[@bs.send]
external on: (notifications, string, (Js.Json.t => unit)) => unit = "on";
let on = (subscriber) => notifications(subscriber) |> on;
