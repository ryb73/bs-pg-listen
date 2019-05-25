open PgListen;
open Js.Promise;

let subscriber = PgListen.make();
onError(subscriber, Js.log2("errrrrrr"));
onNotification(subscriber, ({ channel, payload }) =>
    Js.log3("onNotif", channel, payload));
on(subscriber, "blah", Js.log2("blah"));

connect(subscriber)
|> then_(_ => listenTo(subscriber, "blah"))
|> then_(v => {
    Js.log2("listened", v);
    notify(subscriber, "blah", Obj.magic({"heyyy":"yo"}));
})
|> then_(v => {
    Js.log2("notified", v);
    resolve();
})
|> catch(exn => {
    Js.log2("error:", exn);
    resolve();
});
