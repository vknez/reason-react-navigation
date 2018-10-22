type iosIdiom =
  | Phone
  | Pad
  | TV;

[@bs.module "react-native"] [@bs.scope "Platform"]
external _ios_isPad: bool = "isPad";

[@bs.module "react-native"] [@bs.scope "Platform"]
external _ios_isTVOS: bool = "isTVOS";

type os =
  | IOS(iosIdiom)
  | Android;

[@bs.module "react-native"] [@bs.scope "Platform"] external _os: string = "OS";

exception UnknownPlatform(string);

let os = () =>
  switch (_os) {
  | "ios" =>
    switch (_ios_isPad) {
    | true => IOS(Pad)
    | _ =>
      switch (_ios_isTVOS) {
      | true => IOS(TV)
      | _ => IOS(Phone)
      }
    }
  | "android" => Android
  | x => raise(UnknownPlatform(x))
  };

let equals = targetOs => targetOs === os();

[@bs.module "react-native"] [@bs.scope "Platform"]
external _version: Js.undefined(int) = "Version";

exception UnknownVersion;

let version = () =>
  switch (Js.Undefined.toOption(_version)) {
  | Some(v) => v
  | None => raise(UnknownVersion)
  };
