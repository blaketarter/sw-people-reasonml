type results = {
  results: Types.people
};

let decodePersonList = (json): Types.person => {
  Json.Decode.{
    url: field("url", string, json),
    name: field("name", string, json)
  }
};

let decodeResults = (json): Types.people => {
  Json.Decode.field("results", Json.Decode.array(decodePersonList), json)
};

let get = () => Js.Promise.(
  Fetch.fetch("https://swapi.co/api/people")
  |> then_(Fetch.Response.json)
  |> then_(json => decodeResults(json) |> resolve)
);
