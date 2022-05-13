const fetch = require('cross-fetch');

async function postPRInfo(url, owner, repo, prNumber, runId) {
    const data = {
        owner: owner,
        repo: repo,
        pr_number: prNumber,
        run_id: runId
    };

    const response = await fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    });

    if (!response.ok) {
        throw new Error(`Request failed with status ${response.status}`)
    }

    return response;
}

module.exports = postPRInfo;
