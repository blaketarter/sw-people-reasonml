type personList = array(person)
and person = {
  name: string
};

type results = {
  results: array(person)
};

type state = {
  personList,
};

type action = 
  | AddPeople(personList);

let personListToComponents = (l: personList) => Array.map((p) => <Person name=p.name />)(l);

module DecodeResponse {
  let decodePersonList = (json): person => {
    Json.Decode.{
      name: field("name", string, json)
    }
  };
  
  let decodeResults = (json): personList => {
    Json.Decode.{
      results: field("results", array(decodePersonList), json)
    }.results;
  }
};

let fetchPeople = (reduce) => Js.Promise.(
  Fetch.fetch("https://swapi.co/api/people")
  |> then_(Fetch.Response.json)
  |> then_(json => DecodeResponse.decodeResults(json) |> resolve)
  |> then_(json => reduce(json) |> resolve)
);

let component = ReasonReact.reducerComponent("People");
let make = (_children) => {
  ...component,
  initialState: () => { personList: [||] },
  reducer: (action, _state) =>
    switch action {
      | AddPeople(personList) => ReasonReact.Update({ personList: personList })
    },
  didMount: ({ reduce }) => {
    fetchPeople(reduce(results => AddPeople(results))) |> ignore;
    NoUpdate
  },
  render: ({ state }) => {
    let people = personListToComponents(state.personList);

    <div>
      <h1>(ReasonReact.stringToElement("Star Wars People"))</h1>
      (ReasonReact.arrayToElement(people))
    </div>
  }
};
