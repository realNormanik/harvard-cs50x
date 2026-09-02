import { ApolloClient, InMemoryCache, HttpLink } from "@apollo/client";

export const createApolloClient = (token) => {
  const httpLink = new HttpLink({
    uri: "/api/Sf19GHAdWc",
    headers: {
      authorization: token ? `Bearer ${token}` : "",
      "content-type": "application/json",
    },
  });

  return new ApolloClient({
    link: httpLink,
    cache: new InMemoryCache(),
    defaultOptions: {
      watchQuery: {
        fetchPolicy: "no-cache",
      },
      query: {
        fetchPolicy: "no-cache",
      },
    },
  });
};