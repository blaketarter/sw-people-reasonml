type state = {
  people: Types.people,
};

type action = 
  | AddPeople(Types.people);

let addPeopleReduce = (reduce) => (p) => reduce(r => AddPeople(r), p) |> Js.Promise.resolve;

let component = ReasonReact.reducerComponent("People");
let make = (_children) => {
  ...component,
  initialState: () => { people: [||] },
  reducer: (action, _state) =>
    switch action {
      | AddPeople(people) => ReasonReact.Update({ people: people })
    },
  didMount: ({ reduce }) => {
    PeopleResource.get() |> Js.Promise.then_(addPeopleReduce(reduce)) |> ignore;
    ReasonReact.NoUpdate
  },
  render: ({ state }) => {
    let people = Array.map((p: Types.person) => <Person name=p.name key=p.url />, state.people);
    <div>
      <h1>(ReasonReact.stringToElement("Star Wars People"))</h1>
      (ReasonReact.arrayToElement(people))
    </div>
  }
};
